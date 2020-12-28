$gtk.ffi_misc.gtk_dlopen("ascii_console")

module ASCIIConsole
  include FFI::ASCIIConsole

  include 
  def self.pack_color(red,green,blue,alpha)
    (alpha<<24) + (red<<16) + (green<<8) + blue
  end

  def self.unpack_color(packed_color)
    blue  = packed_color & 0xff
    green = ( packed_color & 0xff00 ) >> 8
    red   = ( packed_color & 0xff0000 ) >> 16
    alpha = ( packed_color & 0xff000000) >> 24

    [ red, green, blue, alpha ]
  end
end
