# shell

## Execution Sequence
1. make
2. ./shell </br>
shell is ready to take command

</br>

## Functinalities and Description
1. Builtin shell commands supported. eg: cat, pwd, ls, echo , clear.. </br>

2. IO Redirection > and >> </br>
![io](https://user-images.githubusercontent.com/28507452/71474130-1a070480-2800-11ea-957f-3aa161131e83.png)

3. Pipe command </br>
![Screenshot from 2019-12-26 16-55-55](https://user-images.githubusercontent.com/28507452/71474335-fc866a80-2800-11ea-995e-bff5ab62791b.png)

4. Command history using commad 'history'

5. Aliasing of command </br>
![Screenshot from 2019-12-21 16-55-23](https://user-images.githubusercontent.com/28507452/71474696-aadedf80-2802-11ea-8bfc-27d0837e6118.png)

6. Mulitple Alarm handling </br>
eg: alaram 2 "Message" <br/>
After 2 seconds Message will be displayed.</br>
If alarm is set and after that shell is closed, So whenever another shell is started all missed alarm will be displayed and remaining alarm will be reset for that shell. 
![Screenshot from 2019-12-20 18-50-57](https://user-images.githubusercontent.com/28507452/71474866-820b1a00-2803-11ea-8b2d-a794d590de8a.png)
As you can see in above screenshot alarm with 'bi' message is missed so when new shell is opened Missed alarm with bi message is displayed. And alarm with msg1 is displayed in second shell even it was set by first shell.

7. Support of shelrc file (similar to bashrc file in bash)
  Using bashrc file we can 
  - Modify default value of environment variables (HOME, PATH, HOSTNAME, USER, PS1 )
  - Add local variables visible to all shells
  - Add alias visible to all shells
  - Change default application for resplective extension
  ![Screenshot from 2019-12-23 17-54-19](https://user-images.githubusercontent.com/28507452/71475477-65bcac80-2806-11ea-845a-806ad81df874.png)

  
