# Buzea Alexandru-Mihai-Iulian 311CAb
build: 
	gcc *.c *.h -o image_editor -Wall -Wextra -lm
clean:
	rm -f image_editor
.PHONY: clean