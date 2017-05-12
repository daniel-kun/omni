COMPILE-SUFFIX = -compiled

MAIN = Main.elm
STYLE-DIR = style
JS-TARGET = Main$(COMPILE-SUFFIX).js
HTML-TARGET = index$(COMPILE-SUFFIX).html

OUTPUT-DIR = output


all: build

build: build-js

serve: build serve-start open

stop: serve-stop clean

open:
	open http://localhost:8080


build-js:
	elm-make $(MAIN) --output=$(OUTPUT-DIR)/$(JS-TARGET)

build-html:
	elm-make $(MAIN) --output=$(OUTPUT-DIR/$(HTML-TARGET)


serve-start:
	StartServer.bat

serve-stop:
	StopServer.bat

# Clean up after yourself
clean:
	rm -f $(OUTPUT-DIR)/*$(COMPILE-SUFFIX).js
	rm -f $(OUTPUT-DIR)/*$(COMPILE-SUFFIX).html
	rm -f $(OUTPUT-DIR)/style/*$(COMPILE-SUFFIX).css*

# Install development dependencies, if needed
dev-dependencies:
	npm install -g livereload
	npm install -g http-server
	npm install -g sass
