#pragma once

///////////////////////////////////////////////////////////////////////////////
//	* My Function . h
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//	* Release Objects
template <typename Release_Object> void ReleaseObjects(Release_Object& object) { SAFE_RELEASE(object); }
template <typename First_Release_Object, typename... Release_Objects> void ReleaseObjects(First_Release_Object& first, Release_Objects&... objects)
{
	SAFE_RELEASE(first);
	ReleaseObjects(objects...);
}

///////////////////////////////////////////////////////////////////////////////
//	* Delete Objects
template <typename Delete_Object> void DeleteObjects(Delete_Object& object) { SAFE_DELETE(object); }
template <typename First_Delete_Object, typename... Delete_Objects> void DeleteObjects(First_Delete_Object& first, Delete_Objects&... objects)
{
	SAFE_DELETE(first);
	DeleteObjects(objects...);
}


