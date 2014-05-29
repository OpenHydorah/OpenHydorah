{-# LANGUAGE ForeignFunctionInterface #-}

module OpenHydorah.Input where

import OpenHydorah.Engine
import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign import ccall "input_preset_get_action_value" c_input_preset_get_action_value
	:: Ptr (a) -> CString -> CInt

foreign import ccall "input_get_max_value" c_input_get_max_value
	:: CInt

action_value engine str = withCAString str (\cstr -> return $ (input cstr) / max)
	where
		preset = c_engine_get_current_input_preset engine
		input str = fromIntegral (c_input_preset_get_action_value preset str)
		max = fromIntegral c_input_get_max_value
