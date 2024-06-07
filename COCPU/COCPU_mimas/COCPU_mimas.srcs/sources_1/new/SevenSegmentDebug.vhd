library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity RunningSevenSegment is
   port (
     Clk              : in  std_logic;  -- Clock signal
     Reset            : in  std_logic;  -- Asynchronous reset (actually synchronous)
     Disable          : in  std_logic;  -- Input to disable counting and hold display at zero
     SevenSegment     : out std_logic_vector(7 downto 0);  -- Seven segment outputs
     DP               : out std_logic   -- Decimal point, not used in this example
   );
end RunningSevenSegment;

architecture Behavioral of RunningSevenSegment is
   -- Internal signals
   signal count      : unsigned(3 downto 0) := "0000"; -- Counter for digits 0 to 9
   signal seg_signal : std_logic_vector(7 downto 0);
   signal slow_clk   : std_logic := '0';  -- Slower clock signal
   signal clk_divider: integer := 0;      -- Clock divider counter
   signal disabled   : std_logic := '0';  -- State to hold the disable condition

begin

   -- Clock divider process to achieve 15 Hz
   clock_divider_process: process(Clk, Reset)
   begin
     if Reset = '1' then
        clk_divider <= 0;
        slow_clk <= '0';
     elsif rising_edge(Clk) then
        if clk_divider >= 666666 then  -- approximately 3333333 for 15 Hz
           slow_clk <= not slow_clk;
           clk_divider <= 0;
        else
           clk_divider <= clk_divider + 1;
        end if;
     end if;
   end process;

   -- Handle Disable and Reset inputs
   disable_process: process(Clk, Disable, Reset)
   begin
     if Reset = '1' then
        disabled <= '0';  -- Clear the disable state on reset
     elsif rising_edge(Clk) then
        if Disable = '1' then
            disabled <= '1';  -- Set the disable state when Disable input is asserted
        end if;
     end if;
   end process;

   -- Process for counting, now affected by Disable and Reset
   counter_process: process(slow_clk, Reset)
   begin
     if Reset = '1' then
        count <= "0000"; -- Reset count to 0
     elsif rising_edge(slow_clk) then
        if count = 5 then
          count <= "0000"; -- Reset to 0 after 5
        else
          count <= count + 1; -- Increment count
        end if;
     end if;
   end process;

   -- Process to control the seven-segment display
   display_process: process(count, disabled)
   begin
     if disabled = '1' then
       seg_signal <= "11111110"; -- Display 0 when disabled
     else
       case count is
         when "0000" => seg_signal <= "01111111"; -- 0
         when "0001" => seg_signal <= "10111111"; -- 1
         when "0010" => seg_signal <= "11011111"; -- 2
         when "0011" => seg_signal <= "11101111"; -- 3
         when "0100" => seg_signal <= "11110111"; -- 4
         when "0101" => seg_signal <= "11111011"; -- 5
         when others => seg_signal <= "00000001"; -- Default to blank
       end case;
     end if;
   end process;

   -- Assign output
   SevenSegment <= seg_signal;
   DP <= '1'; -- DP off
end Behavioral;
