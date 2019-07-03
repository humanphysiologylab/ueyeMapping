HOW TO INSTALL
1.Install IDS Software Suite for Linux from here: https://en.ids-imaging.com/download-ueye-lin64.html (you have to be logged in, registration is free and doesn't require any serial numbers)
2.Make sure that "$ ueyedemo" launches a program and that the "open the ueye" button opens the connected camera and live picture appears on the screen
HOW TO CAPTURE SEQUENCES
1.Launch "$ ./ueyedemo/ueyedemo" from this folder
2.Open the camera
3.Click "properties" button (a wrench icon)
4.On the tab "Size" for both horizontal and vertical formats tick subsampling 2x;
  For the AOI (area of interest), set both Width and Height to 120
  Adjust the position of AOI with "Left" and "Top" sliders
5.On the "Camera" tab set framerate to the desired value (snaps to the closest possible)
6.When camera's position, diaphragm, focus and lighting are adjusted, on the tab "Format" select Hardware 10-bit test. The live picture will get corrupted, but captured sequences look fine.
7.Click the "Save Image" button and enter the desired length of capture in the terminal. The recording will start immediately after you press Enter.
8.Currently you have to close the program and repeat the steps 1-7 to capture another sequence. Recorded sequence is saved as "sequence.bin" in the ueyedemo folder. It is a binary with all the pixels of all the frames as a one-dimension array. The "BinToImg.py" may be modified to find repeating frames, issues with color depth and to view any frame of the footage in matplotlib.
