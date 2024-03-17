library verilog;
use verilog.vl_types.all;
entity EX_3_vlg_sample_tst is
    port(
        A               : in     vl_logic_vector(6 downto 0);
        clock           : in     vl_logic;
        CS              : in     vl_logic;
        D               : in     vl_logic_vector(7 downto 0);
        wren            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end EX_3_vlg_sample_tst;
