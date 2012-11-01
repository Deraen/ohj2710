#ifndef ASSETS_HPP_
#define ASSETS_HPP_
#include <string>
#include <map>
#include "Box2D/Box2D.h"

class Sprite;

class Assets {
public:
    Assets() {};
    ~Assets() {};

    static Assets& instance();

    void init();

    struct Type {
        b2FixtureDef* def;
        Sprite* sprite;
        b2Vec2 meters;
    };

    Type info(const std::string& class_, const std::string& type) const
    {
        auto f1 = types_.find(class_);
        if (f1 != types_.end()) {
            auto f2 = f1->second.find(type);
            if (f2 != f1->second.end()) {
                return f2->second;
            }
        }
        return Type();
    }
private:
    std::map<std::string, std::map<std::string, Type>> types_;
};
#endif /* ASSETS_HPP_ */
