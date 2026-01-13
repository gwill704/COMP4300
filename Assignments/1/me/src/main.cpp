#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <fstream>

#include <imgui-SFML.h>
#include <imgui.h>

struct RGB
{
    u_short red;
    u_short green;
    u_short blue;
};

struct BOOL2D
{
    bool x;
    bool y;
};


class ImGui_struct
{
public:
    bool drawCircle = true;
    bool drawText   = true;
    float circleScale = 1.0f;
    std::size_t   circleSegments = 32;
    sf::Vector2f circleSpeed;
    // the imgui color {r, g, b} wheel requires floats from 0 and 1
    // sfml will require instead of uint8_t from 0-255
    float c[3] = { 0.0f, 0.0f, 0.0f };
    char displayString[255] = "";
};


class Circle : public sf::CircleShape
{
    ImGui_struct m_imgui;
public:
    using sf::CircleShape::CircleShape;
    Circle(float radius = (0.0F) , const char* name = "Circle", const sf::Vector2f& speed = sf::Vector2f(0,0), std::size_t pointCount = 32UL) 
                :   CircleShape(radius, pointCount)
    {
        m_imgui.circleSegments = pointCount;
        this->setScale(m_imgui.circleScale, m_imgui.circleScale);
        this->setPointCount(m_imgui.circleSegments);
    }
    void setSpeed(const sf::Vector2f& speed)
    {
        m_imgui.circleSpeed = speed;
    }
    void setName(const char* name)
    {
        std::strcpy(m_imgui.displayString, name);
    }
    const sf::Vector2f getSpeed() const 
    {
        return m_imgui.circleSpeed;
    }
    const std::string getName() const
    {
        return m_imgui.displayString;
    }
    const std::array<sf::Vector2f, 2> getBoundingBox() const
    {
        sf::Vector2f up_left, down_right;
        up_left = this->getPosition();
        down_right = (up_left + sf::Vector2f(2 * this->getRadius(), 2 * this->getRadius())) * this->getScale().x;
        std::array<sf::Vector2f, 2> boundingBox = {up_left, down_right};
        return boundingBox;
    }
    ImGui_struct& getImGuiPars()
    {
        return m_imgui;
    }
};


class Rectangle : public sf::RectangleShape
{
    ImGui_struct m_imgui;
public:
    using sf::RectangleShape::RectangleShape;
    Rectangle(const sf::Vector2f& size = sf::Vector2f(0, 0), const char* name = "Rectangle", const sf::Vector2f& speed = sf::Vector2f(0,0)) 
    : RectangleShape(size) 
    {
        this->setScale(m_imgui.circleScale, m_imgui.circleScale);
    }

    void setSpeed(const sf::Vector2f& speed)
    {
        m_imgui.circleSpeed = speed;
    }
    void setName(const char* name)
    {
        std::strcpy(m_imgui.displayString, name);
    }
    const sf::Vector2f getSpeed() const 
    {
        return m_imgui.circleSpeed;
    }
    const std::string getName() const
    {
        return m_imgui.displayString;
    }
    const std::array<sf::Vector2f, 2> getBoundingBox() const
    {
        sf::Vector2f up_left, down_right;
        up_left = this->getPosition();
        down_right = (up_left + this->getSize()) * this->getScale().x;
        std::array<sf::Vector2f, 2> boundingBox = {up_left, down_right};
        return boundingBox;
    }
    ImGui_struct& getImGuiPars()
    {
        return m_imgui;
    }
};

class Config
{
    sf::Vector2i m_window_dimensions;
    sf::RenderWindow m_window;
    sf::Text m_text;
    sf::Font m_font;
    std::vector<std::shared_ptr<sf::Shape>> m_shapes;
    std::vector<std::string> m_shapes_names;
public:
    Config() 
    {
        const std::string& filename = std::string(ASSETS_PATH) + "bin/config.txt";
        std::ifstream fin(filename);
        if (!fin.is_open())
        {
            std::cerr << "ERROR: Default constructor Config() tried to read config.txt from " << filename 
                      << " maybe it doesn't exist" << std::endl;
            exit(-1);
        }

        // WINDOW
        std::string instruction;

        fin >> instruction;
        if (instruction != "Window")
        {
            std::cerr << "ERROR: Incorrect format of config.txt file" << std::endl;
            exit(-1);
        }
        fin >> m_window_dimensions.x >> m_window_dimensions.y;
        m_window.create(sf::VideoMode(m_window_dimensions.x, m_window_dimensions.y), "Shapes!");
        m_window.setFramerateLimit(60);


        // FONT
        std::string font_path;
        int font_size;
        RGB font_color;

        fin >> instruction;
        if (instruction != "Font")
        {
            std::cerr << "ERROR: Incorrect format of config.txt file" << std::endl;
            exit(-1);
        }
        fin >> font_path;
        if (!m_font.loadFromFile(std::string(ASSETS_PATH) + font_path))
        {
            std::cerr << "ERROR: Could not load font\n";
            exit(-1);
        }
        fin >> font_size >> font_color.red >> font_color.green >> font_color.blue;

        m_text.setFont(m_font);
        m_text.setCharacterSize(font_size);
        m_text.setFillColor(sf::Color(font_color.red, font_color.green, font_color.blue));
        
        // SHAPES
        std::string shape_name;
        sf::Vector2f shape_initial_position;
        sf::Vector2f shape_initial_speed;
        RGB shape_color;
        float circ_radius;
        sf::Vector2f rect_size;

        while (fin >> instruction)
        {
            if (instruction == "Circle")
            {
                fin >> shape_name >> shape_initial_position.x >> shape_initial_position.y
                >> shape_initial_speed.x >> shape_initial_speed.y 
                >> shape_color.red >> shape_color.green >> shape_color.blue
                >> circ_radius;

                std::shared_ptr<Circle> circle = std::make_shared<Circle>(circ_radius);
                circle->setFillColor(sf::Color(shape_color.red, shape_color.green, shape_color.blue));
                circle->setPosition(shape_initial_position);
                circle->setSpeed(shape_initial_speed);
                circle->setName(shape_name.c_str());
                m_shapes.push_back(circle);
                m_shapes_names.push_back(shape_name);
            }
            else if (instruction == "Rectangle")
            {
                fin >> shape_name >> shape_initial_position.x >> shape_initial_position.y
                >> shape_initial_speed.x >> shape_initial_speed.y 
                >> shape_color.red >> shape_color.green >> shape_color.blue
                >> rect_size.x >> rect_size.y;

                std::shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>(rect_size);
                rectangle->setFillColor(sf::Color(shape_color.red, shape_color.green, shape_color.blue));
                rectangle->setPosition(shape_initial_position);
                rectangle->setSpeed(shape_initial_speed);
                rectangle->setName(shape_name.c_str());
                m_shapes.push_back(rectangle);
                m_shapes_names.push_back(shape_name);
            }
            else 
            {
                std::cerr << "ERROR: Only Circles and Rectangles allowed in config.txt file" << std::endl;
                exit(-1);
            }
        }
        fin.close();

    }

    const sf::Vector2i getWindowSize() const
    {
        return m_window_dimensions;
    }

    sf::Text getTextStyle() const
    {
        return m_text;
    }

    std::vector<std::shared_ptr<sf::Shape>>& getShapes()
    {
        return m_shapes;
    }

    std::vector<std::string>& getShapesNames()
    {
        return m_shapes_names;
    }

    sf::RenderWindow& getWindow()
    {
        return m_window;
    }
};
class Collisions
{
    const sf::Vector2i m_windowSize;
    const sf::FloatRect m_boundingBox;
public:
    Collisions(const Config& config, std::shared_ptr<Circle> shape) : 
    m_windowSize(config.getWindowSize()),
    m_boundingBox(shape->getGlobalBounds())
    {}

    Collisions(const Config& config, std::shared_ptr<Rectangle> shape) : 
    m_windowSize(config.getWindowSize()),
    m_boundingBox(shape->getGlobalBounds())
    {}

    bool shapeIsCollidingX() const
    {
        if (m_boundingBox.getPosition().x < 0 || m_boundingBox.getPosition().x + m_boundingBox.getSize().x > m_windowSize.x)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    bool shapeIsCollidingY() const
    {
        if (m_boundingBox.getPosition().y < 0 || m_boundingBox.getPosition().y + m_boundingBox.getSize().y > m_windowSize.y)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};
class RenderName
{
    Config& m_config;
    sf::Text name;
public:
    RenderName(Config& config, const std::shared_ptr<Circle> circle) : m_config(config), name(config.getTextStyle()) 
    {
        sf::Vector2f position = circle->getPosition();
        position.x += circle->getRadius();
        position.y += circle->getRadius();
        name.setString(circle->getName());
        sf::FloatRect bounds = name.getLocalBounds();
        sf::Vector2f origin = sf::Vector2f(bounds.left + bounds.width/2.f, 
                                           bounds.top + bounds.height/2.f);
        name.setOrigin(origin);

        name.setPosition(position);
    }

    RenderName(Config& config, const std::shared_ptr<Rectangle> rectangle) : m_config(config), name(config.getTextStyle())
    {
        sf::Vector2f position = rectangle->getPosition();
        sf::Vector2f size = rectangle->getSize();
        position.x += size.x/2;
        position.y += size.y/2;
        name.setString(rectangle->getName());
        sf::FloatRect bounds = name.getLocalBounds();
        sf::Vector2f origin = sf::Vector2f(bounds.left + bounds.width/2.f, 
                                           bounds.top + bounds.height/2.f);
        name.setOrigin(origin);

        name.setPosition(position);
    }

    void draw() const
    {
        sf::RenderWindow& window = m_config.getWindow();
        window.draw(name);
    }

    const sf::Text getName() const
    {
        return name;
    }
};



class Movement
{
    Config& m_config;
    std::shared_ptr<sf::Shape> m_shape;
    sf::RenderWindow& window;
public:
    Movement(Config& config, std::shared_ptr<sf::Shape> shape) : m_config(config), m_shape(shape),  window(m_config.getWindow())  {}

    void Update()
    {
        if (auto circle = std::dynamic_pointer_cast<Circle>(m_shape))
        {
            Collisions colision(m_config, circle);
            sf::Vector2f initial_position = circle->getPosition();
            sf::Vector2f speed = circle->getSpeed();
            RenderName rn(m_config, circle);
            rn.draw();
            speed.x = colision.shapeIsCollidingX() ? -speed.x : speed.x;
            speed.y = colision.shapeIsCollidingY() ? -speed.y : speed.y;
            circle->setSpeed(speed);
            sf::Vector2f new_position = initial_position + speed;
            circle->setPosition(new_position);
        }
        else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(m_shape))
        {
            Collisions colision(m_config, rectangle);
            sf::Vector2f initial_position = rectangle->getPosition();
            sf::Vector2f speed = rectangle->getSpeed();
            RenderName rn(m_config, rectangle);
            rn.draw();
            speed.x = colision.shapeIsCollidingX() ? -speed.x : speed.x;
            speed.y = colision.shapeIsCollidingY() ? -speed.y : speed.y;
            rectangle->setSpeed(speed);
            sf::Vector2f new_position = initial_position + speed;
            rectangle->setPosition(new_position);
        }
        else
        {
            std::cerr << "ERROR: Something went wrong, a shape is not a Rectangle nor a Circle\n";
            exit(-1);
        }
    }
};


class RenderShapes
{
    std::vector<std::shared_ptr<sf::Shape>> m_shapes;
    Config& m_config;
public:
    RenderShapes(Config& config) : m_config(config)
    {
        m_shapes = config.getShapes();
    }

    void draw()
    {
        sf::RenderWindow& window = m_config.getWindow();

        for (auto shape : m_shapes)
        {
            if (auto circle = std::dynamic_pointer_cast<Circle>(shape))
            {
                if (circle->getImGuiPars().drawCircle)
                {
                    circle->setScale(circle->getImGuiPars().circleScale, circle->getImGuiPars().circleScale);
                    window.draw(*circle);  
                }          
            }
            else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(shape))
            {
                if (rectangle->getImGuiPars().drawCircle)
                {
                    rectangle->setScale(rectangle->getImGuiPars().circleScale, rectangle->getImGuiPars().circleScale);
                    window.draw(*rectangle);  
                }
            }
            // update position 
            Movement m(m_config, shape);
            m.Update();
        }
    }
};


class ImGui_implementation
{
    std::vector<std::string>& m_shapes_names;
    std::vector<std::shared_ptr<sf::Shape>>& m_shape;
    int index = 0;

public:
    ImGui_implementation(Config& config) : m_shape(config.getShapes()), m_shapes_names(config.getShapesNames())
    {}

    void draw()
    {
        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        std::vector<const char*> names;
        for (auto& name : m_shapes_names)
        {
            names.push_back(name.c_str());
        }
        ImGui::Combo("Shape", &index, names.data(), (int)names.size());
        if (auto circle = std::dynamic_pointer_cast<Circle>(m_shape[index]))
        {
            ImGui_struct& pars = circle->getImGuiPars();
            std::string sindex = std::to_string(index);
            std::string s = "Draw Shape##" + sindex;
            ImGui::Checkbox(s.c_str(), &pars.drawCircle);
            s = "Scale##" + sindex;
            ImGui::SliderFloat(s.c_str(), &pars.circleScale, 0.f, 10.f, "%.3f");
        }
        else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(m_shape[index]))
        {
            ImGui_struct& pars = rectangle->getImGuiPars();
            std::string sindex = std::to_string(index);
            std::string s = "Draw Shape##" + std::to_string(index);
            ImGui::Checkbox(s.c_str(), &pars.drawCircle);
            s = "Scale##" + sindex;
            ImGui::SliderFloat(s.c_str(), &pars.circleScale, 0.f, 10.f, "%.3f");
        }
        ImGui::End();
    }
};


int main (int argc, char * argv[]) 
{
    //create a new window of the size w*h pixels
    // top-left of the window is (0,0) and bottom-right is (w,h)
    Config* config = new Config();
    sf::RenderWindow& window = config->getWindow();
    RenderShapes rs(*config);

    // initialize imgui and create clock for internal timing
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "ERROR: Could not load the window in ImGui\n";
        std::exit(-1);
    }

    sf::Clock deltaClock;

    // scale the imgui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.f;

    ImGui_implementation im(*config);

    // set up the objects that will be drawn to the screen 
    //std::vector<std::shared_ptr<sf::Shape>> shapes = config->getShapes();
    
    // main loop - continues for each frame wile window is open
    while (window.isOpen())
    {
        // event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            
            
            // this event is triggered when a key is processed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    
        // imgui
        ImGui::SFML::Update(window, deltaClock.restart());
        im.draw();

        // basic rendering function calls 
        window.clear(); // clear the window from anything previously drawn
        rs.draw();
        ImGui::SFML::Render(window);
        window.display();    // call the window display funtion (double buffer )
    }

    ImGui::SFML::Shutdown();
}