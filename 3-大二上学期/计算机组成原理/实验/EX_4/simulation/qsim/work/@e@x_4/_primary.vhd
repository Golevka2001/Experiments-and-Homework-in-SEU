library verilog;
use verilog.vl_types.all;
entity EX_4 is
    port(
        CF              : out    vl_logic;
        Yin             : in     vl_logic;
        \BUS\           : out    vl_logic_vector(7 downto 0);
        GRout           : in     vl_logic;
        Clk             : in     vl_logic;
        Clr             : in     vl_logic;
        GRin            : in     vl_logic;
        GRsel           : in     vl_logic;
        IR              : out    vl_logic_vector(7 downto 0);
        IRin            : in     vl_logic;
        Zout            : in     vl_logic;
        Zin             : in     vl_logic;
        MDRout          : in     vl_logic;
        MEMRd           : in     vl_logic;
        MARin           : in     vl_logic;
        MEMWr           : in     vl_logic;
        MDRin           : in     vl_logic;
        PCout           : in     vl_logic;
        PC              : out    vl_logic_vector(7 downto 0);
        PC_1            : in     vl_logic;
        PCin            : in     vl_logic;
        op              : in     vl_logic_vector(1 downto 0);
        \OF\            : out    vl_logic;
        ZF              : out    vl_logic;
        SF              : out    vl_logic
    );
end EX_4;
