{-# LANGUAGE ForeignFunctionInterface #-}

module Hydorah where

import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign export ccall getInfo
	:: IO CString
getInfo = do
	name <- newCAString "Hydorah"
	return name
