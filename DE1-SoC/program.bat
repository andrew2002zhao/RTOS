%QUARTUS_ROOTDIR%\bin64\quartus_pgm.exe -c 1 -m jtag -o "P;DE1_SoC_Computer.sof@2"
%QUARTUS_ROOTDIR%\bin64\quartus_hps.exe -c 1 -o GDBSERVER --gdbport0=3008 --preloader=de1-soc.srec --preloaderaddr=0xffff13a0
