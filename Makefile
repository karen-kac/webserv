NAME = webserv

SRCDIR = src
OBJDIR = obj
INCDIR = inc

SOURCES = main.cpp \
		  Server.cpp \
		  Config.cpp \
		  Request.cpp \
		  Response.cpp \
		  Utils.cpp \
		  CGI.cpp \
		  Location.cpp \
		  HttpParser.cpp

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re