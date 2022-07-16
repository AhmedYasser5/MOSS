# TODO: fix that strange behaviour in build-%
CXX := g++
CXXFLAGS := -pipe -g
MKDIR := mkdir
FORMAT := clang-format
FORMAT_FLAGS := 
LINT := clang-check
LINTFLAGS :=

BUILD_DIR = ./build
SRC_DIR = .

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^

build-%.cpp: $(BUILD_DIR)/%.o

.PHONY: lint-%
lint-%:
	${LINT} ${LINTFLAGS} %.cpp

.PHONY: format-%
format-%:
	${FORMAT} ${FORMAT_FLAGS} %.cpp

.PHONY: list-todos-%
list-todos-%: %
	grep '\<TODO\>: .*\.' $^ -o --color --line-number
