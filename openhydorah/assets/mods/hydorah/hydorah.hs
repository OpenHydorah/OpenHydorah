{-# LANGUAGE ForeignFunctionInterface #-}

module Hydorah where

import OpenHydorah.Engine
import OpenHydorah.Scene
import OpenHydorah.Entity
import OpenHydorah.Input
import Debug.Trace
import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign export ccall get_info
	:: Ptr (CString) -> Ptr (CString) -> IO ()
get_info namePtr descPtr = do
	nameStr <- newCAString "Hydorah"
	poke namePtr nameStr
	descStr <- newCAString "Hydorah mod"
	poke descPtr descStr
	return ()

foreign export ccall mod_init
	:: Ptr a -> IO ()
mod_init engine = do
	traceIO "modInit"
	scene <- newCAString "scenes/test.scene"
	preset <- newCAString "scenes/keymap.set"
	c_engine_load_input_preset engine preset
	c_engine_load_scene engine scene
	free preset
	free scene
	return ()

foreign export ccall mod_destroy
	:: Ptr a -> IO ()
mod_destroy engine = do
	traceIO "modDeinit"
	return ()

foreign export ccall mod_update
	:: Ptr a -> CInt -> IO ()
mod_update engine delta = do
	dt <- return $ (fromIntegral delta) / 1000

	player <- entity_find_first engine "player"
	left <- action_value engine "left"
	right <- action_value engine "right"
	up <- action_value engine "up"
	down <- action_value engine "down"

	entity_translate player ((right - left) * 80 * dt, (down - up) * 80 * dt)

	return ()
