(1) how to setup and run your program<br>

	1. enter the command: ```sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f```
	2. push the button (A1 is used to increase the slew rate, A2 is used to decrease the slew rate)
	3. push the A3 to confirm the frequency of the wave
	4. enter the command: ```sudo python3 FFT.py```
	5. the code FFT.py will output a figure which has two subplots
	(Then we can keep repeating the steps 2~5)
	
接下來是用照片展示我大概如何架設板子和連線的<br>
![image](https://github.com/EricChenSudo/mid1/blob/master/picture/330871.jpg)

![image](https://github.com/EricChenSudo/mid1/blob/master/picture/330874.jpg)

![image](https://github.com/EricChenSudo/mid1/blob/master/picture/330877.jpg)
	   

(2) What are the result<br>

最後面LCD的樣子<br>
![image](https://github.com/EricChenSudo/mid1/blob/master/picture/330867.jpg)

接下來附上當slew rate等於1的時候的執行結果(其餘執行結果在PDF)<br>
![image](https://github.com/EricChenSudo/mid1/blob/master/picture/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202021-04-07%20190300.png)
![image](https://github.com/EricChenSudo/mid1/blob/master/picture/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202021-04-07%20190656.png)

辛苦了!<br>
	
