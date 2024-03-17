library verilog;
use verilog.vl_types.all;
entity EX_3_1_vlg_check_tst is
    port(
        A               : in     vl_logic_vector(7 downto 0);
        \BUS\           : in     vl_logic_vector(7 downto 0);
        RESULT          : in     vl_logic_vector(7 downto 0);
        sampler_rx      : in     vl_logic
    );
end EX_3_1_vlg_check_tst;
