onerror {exit -code 1}
vlib work
vlog -work work EX_3.vo
vlog -work work EX_3_1.vwf.vt
vsim -novopt -c -t 1ps -L cycloneiv_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.EX_3_1_vlg_vec_tst -voptargs="+acc"
vcd file -direction EX_3.msim.vcd
vcd add -internal EX_3_1_vlg_vec_tst/*
vcd add -internal EX_3_1_vlg_vec_tst/i1/*
run -all
quit -f
