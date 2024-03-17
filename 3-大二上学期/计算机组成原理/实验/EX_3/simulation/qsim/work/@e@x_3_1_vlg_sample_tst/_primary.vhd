library verilog;
use verilog.vl_types.all;
entity EX_3_1_vlg_sample_tst is
    port(
        CLOCK           : in     vl_logic;
        G_IN            : in     vl_logic;
        G_MEM           : in     vl_logic;
        G_OUT           : in     vl_logic;
        INPUT           : in     vl_logic_vector(7 downto 0);
        wen_LA          : in     vl_logic;
        wen_MEM         : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end EX_3_1_vlg_sample_tst;
