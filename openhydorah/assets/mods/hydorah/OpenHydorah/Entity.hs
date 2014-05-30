{-# LANGUAGE ForeignFunctionInterface #-}

module OpenHydorah.Entity where

import OpenHydorah.Engine
import OpenHydorah.Scene
import Foreign
import Foreign.Ptr
import Foreign.C.String
import Foreign.C.Types

foreign import ccall "entity_get_sprite" c_entity_get_sprite
	:: Ptr (a) -> Ptr (b)

foreign import ccall "entity_get_name" c_entity_get_name
	:: Ptr (a) -> CString

foreign import ccall "entity_get_parent" c_entity_get_parent
	:: Ptr (a) -> Ptr (b)

foreign import ccall "entity_get_position_x" c_entity_get_position_x
	:: Ptr (a) -> Float

foreign import ccall "entity_get_position_y" c_entity_get_position_y
	:: Ptr (a) -> Float

foreign import ccall "entity_get_number_property" c_entity_get_number_property
	:: Ptr (a) -> CString -> Float

foreign import ccall "entity_get_string_property" c_entity_get_string_property
	:: Ptr (a) -> CString -> CString

foreign import ccall "entity_set_position_x" c_entity_set_position_x
	:: Ptr (a) -> Float -> IO ()

foreign import ccall "entity_set_position_y" c_entity_set_position_y
	:: Ptr (a) -> Float -> IO ()

foreign import ccall "entity_list_find_first" c_entity_list_find_first
	:: Ptr (a) -> CString -> Ptr (b)

foreign import ccall "entity_set_number_property" c_entity_set_number_property
	:: Ptr (a) -> Float -> CString -> IO ()

entity_get_position ent = (x, y)
	where
		x = c_entity_get_position_x ent
		y = c_entity_get_position_y ent

entity_get_number_property ent str = withCAString str (property ent)
	where
		property ent cstr = return $ c_entity_get_number_property ent cstr

entity_get_string_property ent str = withCAString str (property ent)
	where
		property ent cstr = peekCString (c_entity_get_string_property ent cstr)

entity_set_position ent (x,y) =
	do
		c_entity_set_position_x ent x
		c_entity_set_position_y ent y
		return ()

entity_translate ent (dx,dy) =
	do
		entity_set_position ent (x + dx, y + dy)
	where
		(x,y) = entity_get_position ent

entity_find_first engine str =
	do
		scene <- return $ c_engine_get_current_scene engine
		entities <- return $ c_scene_get_entities scene
		ent <- withCString str (\cstr -> do return $ c_entity_list_find_first entities cstr)
		return ent
