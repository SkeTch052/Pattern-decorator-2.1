#include <iostream>
#include <string>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph (Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& link, const std::string& data)  const {
        std::cout << "<a href=";
        text_->render(link);
        std::cout << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main()
{
    auto text = new Text();
    text->render("Hello world");
    std::cout << std::endl;

    auto paragraphed_text = new Paragraph(text);
    paragraphed_text->render("Hello world");
    std::cout << std::endl;

    auto reversed_text = new Reversed(text);
    reversed_text->render("Hello world");
    std::cout << std::endl;

    auto linked_text = new Link(text);
    linked_text->render("netology.ru", "Hello world");
    std::cout << std::endl;

    delete text;
    delete paragraphed_text;
    delete reversed_text;
    delete linked_text;
    return 0;
}