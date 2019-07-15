program rev(input,output);

var
  tmp:string[9];
  m:integer;

begin
  while not(eof) do
  begin
    for m:=1 to 9 do
      read(tmp[m]);
    for m:=9 downto 1 do
      write(tmp[m]);
    readln;
    writeln;
  end;
end.