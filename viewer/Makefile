compile:
	conan install . --output-folder=build --build=missing
	meson setup --native-file ./build/conan_meson_native.ini . ./build/meson-src
	meson compile -C build/meson-src

