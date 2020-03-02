#bin/lottery:src/*.c
#	gcc src/*.c -o bin/lottery -I include

# 目标 ： 依赖
# 	编译指令
# $@	目标
# $< 	依赖

target = bin/server
cc = gcc
object =obj/user_link.o obj/user_handler.o obj/common.o obj/admin.o  obj/user_lottery_link.o obj/nottery.o obj/issue_lottery.o obj/lottery_handler.o  

 


flag = -lpthread -g -Wall -I include

bin/lottery:src/main.c $(object)
	$(cc) src/main.c $(object) -o $@ $(flag)
obj/user_link.o:src/user_link.c
	$(cc) -c $< -o $@ $(flag)
obj/user_handler.o:src/user_handler.c
	$(cc) -c $< -o $@ $(flag)
obj/common.o:src/common.c
	$(cc) -c $< -o $@ $(flag)
obj/admin.o:src/admin.c
	$(cc) -c $< -o $@ $(flag)
obj/user_lottery_link.o:src/user_lottery_link.c
	$(cc) -c $< -o $@ $(flag)
obj/nottery.o:src/nottery.c
	$(cc) -c $< -o $@ $(flag)
obj/issue_lottery.o:src/issue_lottery.c
	$(cc) -c $< -o $@ $(flag)
obj/lottery_handler.o:src/lottery_handler.c
	$(cc) -c $< -o $@ $(flag)


clean:
	rm bin/*
	rm obj/*
