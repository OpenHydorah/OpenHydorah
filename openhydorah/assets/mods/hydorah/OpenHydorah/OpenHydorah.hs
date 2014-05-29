{-# LANGUAGE ForeignFunctionInterface #-}

module OpenHydorah.OpenHydorah where

import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign import ccall "entity_get_name" c_entity_get_name
	:: Ptr (a) -> CString

foreign import ccall "entity_get_position_x" c_entity_get_position_x
	:: Ptr (a) -> CInt

foreign import ccall "entity_get_position_y" c_entity_get_position_y
	:: Ptr (a) -> CInt
