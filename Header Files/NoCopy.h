#pragma once

struct NoCopy
{
	NoCopy() = default;
	~NoCopy() = default;

	NoCopy(const NoCopy&) = delete;
	NoCopy(NoCopy&&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
};