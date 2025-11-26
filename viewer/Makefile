compile:
	conan install . --output-folder=build --build=missing
	meson subprojects download
	meson setup --native-file ./build/conan_meson_native.ini . ./build/meson-src
	meson compile -C build/meson-src

