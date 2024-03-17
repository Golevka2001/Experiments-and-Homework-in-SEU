library verilog;
use verilog.vl_types.all;
entity EX_3 is
    port(
        Q               : out    vl_logic_vector(7 downto 0);
        A               : in     vl_logic_vector(6 downto 0);
        CS              : in     vl_logic;
        clock           : in     vl_logic;
        wren            : in     vl_logic;
        D               : in     vl_logic_vector(7 downto 0)
    );
end EX_3;
