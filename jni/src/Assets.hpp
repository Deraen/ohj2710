#ifndef ASSETS_HPP_
#define ASSETS_HPP_
#include <string>
#include <map>

class Sprite;

class Assets {
public:
    Assets() {};
    ~Assets() {};

    static Assets& instance();

    void init();

    Sprite* getSprite(const std::string& identifier);
private:
    std::map<std::string, Sprite* > sprites_;
};
#endif /* ASSETS_HPP_ */
