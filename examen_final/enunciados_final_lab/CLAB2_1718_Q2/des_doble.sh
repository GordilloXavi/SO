#!/bin/bash

./demux_ok 20> clab2.0 21> clab2.1

./des_ok cesar  < clab2.0 > clab2.0.tmp
./des_ok mirror < clab2.1 > clab2.1.tmp

./mux_ok 20< clab2.0.tmp 21< clab2.1.tmp

