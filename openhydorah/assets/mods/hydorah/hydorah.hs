{-# LANGUAGE ForeignFunctionInterface #-}

module Hydorah where

import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types
import Debug.Trace

foreign export ccall getInfo
	:: Ptr (CString) -> Ptr (CString) -> IO ()
getInfo namePtr descPtr = do
	nameStr <- newCAString "Hydorah"
	poke namePtr nameStr
	descStr <- newCAString "Hydorah mod"
	poke descPtr descStr
	return ()
