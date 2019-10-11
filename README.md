This program will convert an .ai file to a .path file.


You don't need to compile the project, just copy all three .aip files to 
"C:\Program Files\Adobe\Adobe Illustrator CC 2018\Plug-ins"


The first step is to create a 500x500 document, and make sure the color mode is RGB.

![Screenshot 0](https://github.com/azer89/IllustratorPathConverter/blob/master/screenshot0.PNG)

You then draw a shape, make sure it's name is "boundary" or the shape will be ignored by the plugin.
The plugin doesn't care about the layer name.

![Screenshot 1](https://github.com/azer89/IllustratorPathConverter/blob/master/screenshot1.PNG)

The plugin does not support splines, it only reads the anchor points, so the shapes must be sampled.

![Screenshot 2](https://github.com/azer89/IllustratorPathConverter/blob/master/screenshot2.png)

You can add a stroke color and a fill color but make sure the colors are RGB.

Press "Convert to Text File" to generate a .path file

![Screenshot 3](https://github.com/azer89/IllustratorPathConverter/blob/master/screenshot3.png)

Done!

A .path file is just a text file containing polygonal paths, if you are interested in the format, you can read 
".../code/EmptyPanel/Source/PathIO.cpp"
