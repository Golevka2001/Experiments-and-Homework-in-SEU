library verilog;
use verilog.vl_types.all;
entity EX_4_vlg_sample_tst is
    port(
        Clk             : in     vl_logic;
        Clr             : in     vl_logic;
        GRin            : in     vl_logic;
        GRout           : in     vl_logic;
        GRsel           : in     vl_logic;
        IRin            : in     vl_logic;
        MARin           : in     vl_logic;
        MDRin           : in     vl_logic;
        MDRout          : in     vl_logic;
        MEMRd           : in     vl_logic;
        MEMWr           : in     vl_logic;
        op              : in     vl_logic_vector(1 downto 0);
        PC_1            : in     vl_logic;
        PCin            : in     vl_logic;
        PCout           : in     vl_logic;
        Yin             : in     vl_logic;
        Zin             : in     vl_logic;
        Zout            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end EX_4_vlg_sample_tst;
