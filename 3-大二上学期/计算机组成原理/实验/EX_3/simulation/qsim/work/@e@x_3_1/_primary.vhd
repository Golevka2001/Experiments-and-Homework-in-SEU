library verilog;
use verilog.vl_types.all;
entity EX_3_1 is
    port(
        A               : out    vl_logic_vector(7 downto 0);
        wen_LA          : in     vl_logic;
        \BUS\           : out    vl_logic_vector(7 downto 0);
        G_OUT           : in     vl_logic;
        G_MEM           : in     vl_logic;
        CLOCK           : in     vl_logic;
        wen_MEM         : in     vl_logic;
        G_IN            : in     vl_logic;
        INPUT           : in     vl_logic_vector(7 downto 0);
        RESULT          : out    vl_logic_vector(7 downto 0)
    );
end EX_3_1;
