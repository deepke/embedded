在使用SDK前执行build.sh构建SDK环境和使用env.sh设置环境变量



注意:

如果在执行脚本报以下错误

-bash: ./env.sh: /bin/bash^M: bad interpreter: No such file or directory

可以先执行命令 sed -i "s/\r//" env.sh