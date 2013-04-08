## Multicam Image Recognition

An example file to build upon when using dual USB Firefly MV cameras in a travelling computer vision installation. Uses two cameras and ARTK+ to detect markers. Using the two cameras with two markers for redundancy.

## Motivation

Replacement hardware is important, and devices must iterate the same even after the pieces are deinstalled and reassembled. Camera IDs will need to be available to the installer, who can then check their configuration in an external file. 

# Requirements

-ofxOpenCV
-ofxARToolkitPlus
- <a href="http://www.openframeworks.cc/download/">openFrameworks v0.7.4</a>
- ofxXmlSettings
- <a href="https://github.com/camb416/ofxLibdc">ofxLibdc</a>. Only slightly modified from <a href="https://github.com/kylemcdonald/ofxLibdc">kylemacdonald</a>'s original.

#Screenshot

<img src="https://raw.github.com/camb416/pointgrey_multicam/master/screenshot.png" />
