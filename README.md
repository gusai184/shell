# shell

## Execution Sequence
1. make
2. ./shell </br>
shell is ready to take command

</br>

## Functionalities and Description
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

7. Support of shellrc file (similar to bashrc file in bash)
  Using bashrc file we can 
    - Modify default value of environment variables (HOME, PATH, HOSTNAME, USER, PS1 )
    - Add local variables visible to all shells
    - Add alias visible to all shells
    - Change default application for resplective extension
  ![Screenshot from 2019-12-23 17-54-19](https://user-images.githubusercontent.com/28507452/71475477-65bcac80-2806-11ea-845a-806ad81df874.png)
  
8. Default Application launch handling <br/>
  eg: open abc.mp4 (will be launched via default application specified in shellrc file)
  <br/>
  
9. Recording of all input and output to a file </br>
   record start : to start recording </br>
   record stop : to stop recording </br>
   ouput will be stored in record.txt file
   <br/>
   ![Screenshot from 2019-12-26 17-48-49](https://user-images.githubusercontent.com/28507452/71475843-20997a00-2808-11ea-8c88-f4284d6e8962.png)

10. Export command
    export x 
    now x variable will be visible to all child process.
   
11. Support for $$ and $?
 - $$ : Returns terminal id <br/>
 - $? : Status of last exected command <br/> 
        It will return 0 for success and error no for failure.</br>
  ![Screenshot from 2019-12-25 23-20-23](https://user-images.githubusercontent.com/28507452/71476093-5a1eb500-2809-11ea-86b6-78407a1b1814.png)

12. Association of ~ with HOME variable </br>
  As we can do in linux here also we can use ~ instead of HOME variavle anywhere.</br>
  eg. echo ~, cd ~
