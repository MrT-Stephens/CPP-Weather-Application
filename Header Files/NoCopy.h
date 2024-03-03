#pragma once

/// <summary>
/// A struct that can't be copied or moved.
/// This is useful for classes that should not be copied or moved.
/// </summary>
struct NoCopy
{
	NoCopy() = default;
	~NoCopy() = default;

	NoCopy(const NoCopy&) = delete;
	NoCopy(NoCopy&&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
};