CC = cc
CFLAGS = -Wall -Wextra -Werror

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

MANDATORY_SERVER = mandatory/server.c mandatory/utilities.c
MANDATORY_CLIENT = mandatory/client.c mandatory/utilities.c
BONUS_SERVER = bonus/server_bonus.c bonus/utilities_bonus.c
BONUS_CLIENT = bonus/client_bonus.c bonus/utilities_bonus.c

OBJM_SERVER = ${MANDATORY_SERVER:.c=.o}
OBJM_CLIENT = ${MANDATORY_CLIENT:.c=.o}
OBJB_SERVER = ${BONUS_SERVER:.c=.o}
OBJB_CLIENT = ${BONUS_CLIENT:.c=.o}

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

all: ${SERVER} ${CLIENT}

bonus: ${SERVER_BONUS} ${CLIENT_BONUS}

${SERVER}: ${OBJM_SERVER}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${CC} ${CFLAGS} ${OBJM_SERVER} -o ${SERVER}
	@echo "${GREEN}✅ ${SERVER} successfully compiled!${RESET}"

${CLIENT}: ${OBJM_CLIENT}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${CC} ${CFLAGS} ${OBJM_CLIENT} -o ${CLIENT}
	@echo "${GREEN}✅ ${CLIENT} successfully compiled!${RESET}"

${SERVER_BONUS}: ${OBJB_SERVER}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${CC} ${CFLAGS} ${OBJB_SERVER} -o ${SERVER_BONUS}
	@echo "${GREEN}✅ ${SERVER_BONUS} successfully compiled!${RESET}"

${CLIENT_BONUS}: ${OBJB_CLIENT}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${CC} ${CFLAGS} ${OBJB_CLIENT} -o ${CLIENT_BONUS}
	@echo "${GREEN}✅ ${CLIENT_BONUS} successfully compiled!${RESET}"

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJM_SERVER} ${OBJM_CLIENT} ${OBJB_SERVER} ${OBJB_CLIENT}
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	rm -f ${SERVER} ${CLIENT} ${SERVER_BONUS} ${CLIENT_BONUS}
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: bonus clean re
