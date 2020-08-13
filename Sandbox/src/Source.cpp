#include <Leviathan.h>
#include <functional>
#include <iostream>

class Game : public Application {
public:
	Game() = default;
	~Game() = default;

	 void OnEvent(Event* event) override {
		if (event->GetType() != EventType::RefreshEvent) {
			std::cout << event->GetString() << std::endl;
		}
	 }
};
int main() {
	std::shared_ptr<Game> app = std::make_shared<Game>();
	app->Run();
	app.reset();
	return 1;
}