library verilog;
use verilog.vl_types.all;
entity EX_4_vlg_check_tst is
    port(
        \BUS\           : in     vl_logic_vector(7 downto 0);
        CF              : in     vl_logic;
        IR              : in     vl_logic_vector(7 downto 0);
        \OF\            : in     vl_logic;
        PC              : in     vl_logic_vector(7 downto 0);
        SF              : in     vl_logic;
        ZF              : in     vl_logic;
        sampler_rx      : in     vl_logic
    );
end EX_4_vlg_check_tst;
