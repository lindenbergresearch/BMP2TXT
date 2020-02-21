# BMP2TXT
#### Bitmap to Textfile converter for 1-Bit bitmap fonts for usage in Propeller SPIN DAT sections.
*Version 0.0.9a*  

__This is still an alpha version, just for testing purpose.__
Written for creating fonts for LRT/OS. All rights MIT licensed.

* supports 8x16 per character bitmap fonts *(DOS like)*
* supports Windows bitmap file format encoded with a 1-Bit color depth
* bitmap resolution __must__ be a multiple of 8x16 pixels
* bitmap size __must__ fit to hold 256 characters
* used grid-dimensions of characters currently will be autodetected:  
  16 x 16 characters result in a 128px by 256px bitmap and 256 characters  
  256 x 1 characters result in 2048px by 16px bitmap and 256 characters  
  other examples are: 8x32, 4x64 etc.
* prints optional a test text to console using the current font-data  
  
  _WARNING:_   
  Printing long texts to console may result in unwanted linebrakes, be aware that you need 8x16 chars space per letter!
* prints header information read from bitmap file

[LRT, January 2017]
