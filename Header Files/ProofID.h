#pragma once

#include <string>

class ProofID
{
private:
	std::string m_ProofID;
public:
	ProofID() { }
	ProofID(const std::string& proofID) : m_ProofID(proofID) { }
	~ProofID() { m_ProofID = ""; }

	std::string GetProofID() const { return m_ProofID; }

	bool operator==(const ProofID& other) const { return m_ProofID == other.m_ProofID; }
};