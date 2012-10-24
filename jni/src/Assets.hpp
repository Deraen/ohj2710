#ifndef ASSETS_HPP_
#define ASSETS_HPP_
#include <string>
#include <map>
class Assets {
public:
    Assets() {};
    ~Assets() {};

    static Assets& instance();

    void init();

    unsigned int getSprite(const std::string& identifier);
private:
    std::map<std::string, unsigned int> sprites_;
};
#endif /* ASSETS_HPP_ */
