class rdjki : public Fijk
{
    private:
        u32 _addr;

    public:
        rdjki(u08 i, u08 j, u08 k) : Fijk(0xD, i, j, k) {}
        rdjki() : Fijk(0xD, 0, 0, 0) {}
        bool execute()
        {
            u64 addr = (PROC[me()].X(_j).i() + PROC[me()].X(_k).i()) & 0xfffff;	// Compute displacement
            stringstream ss;
            if (addr < PROC[me()].FL().u()*256 )		    // Is displacement within bounds of field length
            {
                // Good
                addr += PROC[me()].RA().u()*256;		    // Add reference address
                assert(addr >= 0);			    // Address should be nonnegative
                assert(addr < params::MEM::N);              // Check against hardware limit
                PROC[me()].X(_i) = MEM[addr];                     // Read data
                _addr = addr;				    // Save read address

                ss << setfill('0') << setw(16) << hex << addr << " "
                    << setw(16) << PROC[me()].X(_i).i() << " " << dec <<
                    setfill(' ');
            }
            else
            {
                // Bad
                PROC[me()]._XA = PROC[me()].XA().u();
                PROC[me()].cond()(2) = true;
                assert(false);
            }
            _trace = ss.str();
            return false;
        }

        string mnemonic() const
        {
            return "rdjki";
        }

        bool ops()
        {
            operations::process<operations::agen>(params::micro::Xs, _j, _k, 0);
            operations::process<operations::rdw>(_i, params::micro::Xs, _addr);
            return false;
        }

        bool match(u08 F)
        {
            return _F == F;
        }

        void decode(u32 code)
        {
            assert(code < 65536);       // 16-bit instruction
            assert(match(code >> 12));  // we are in the right instruction
            _i = (code >> 8) & 0xf;     // extract i
            _j = (code >> 4) & 0xf;     // extract j
            _k = code  & 0xf;           // extract k
        }

    vector<operations::operation*> crack()
	{
	    vector<operations::operation*>	ops;
	    ops.push_back(new operations::agen(params::micro::Xs, _j, _k, 0));
	    ops.push_back(new operations::rdw(_i,  params::micro::Xs));
	    return ops;
    }
};
