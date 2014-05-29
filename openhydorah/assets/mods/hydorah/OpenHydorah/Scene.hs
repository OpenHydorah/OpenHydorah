{-# LANGUAGE ForeignFunctionInterface #-}

module OpenHydorah.Scene where

import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign import ccall "scene_get_entities" c_scene_get_entities
	:: Ptr (a) -> Ptr (b)
