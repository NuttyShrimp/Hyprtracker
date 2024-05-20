.PHONY: all debug release clean install dev

debug:
	cmake -B ./Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$(PREFIX)
	cmake --build ./Debug -j
	rm -rf ./hyprtracker.so
	ln -s ./Debug/hyprtracker.so .

release:
	cmake -B ./Release -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(PREFIX)
	cmake --build ./Release -j
	rm -rf ./hyprtracker.so
	ln -s ./Release/hyprtracker.so .

all: clean release

clean:
	rm -rf Release
	rm -rf Debug
	rm -rf ./hyprtracker.so

install: release
	mkdir -p `xdg-user-dir`/.config/hypr/plugins
	cp hyprtracker.so `xdg-user-dir`/.config/hypr/plugins

dev: clean debug