{-# LANGUAGE ForeignFunctionInterface #-}

module OpenHydorah.Engine where

import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign import ccall "engine_get_current_scene" c_engine_get_current_scene
	:: Ptr (a) -> Ptr (b)

foreign import ccall "engine_get_current_input_preset" c_engine_get_current_input_preset
	:: Ptr (a) -> Ptr (b)

foreign import ccall "engine_load_scene" c_engine_load_scene
	:: Ptr (a) -> CString -> IO ()

foreign import ccall "engine_load_input_preset" c_engine_load_input_preset
	:: Ptr (a) -> CString -> IO ()
