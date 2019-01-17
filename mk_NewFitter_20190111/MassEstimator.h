namespace MassEstimator
{
	// particle masses in MeV
	const Double_t amu   = 931.478;
	const Double_t kmpi  = 139.57018;
	const Double_t kmp   = 938.2720813;
	const Double_t kmd   = 1875.612762;
	const Double_t kmt   = 2808.921112;
	const Double_t kmhe3 = 2808.39132;
	const Double_t kmal  = 3727.379378;
	const Double_t kmhe6 = 6.0188*amu;
	const Double_t kmli6 = 6.0151*amu;
	const Double_t kmli7 = 7.016*amu;
	const Double_t kme   = 0.5109989461;

	// Bethe-Bloch and Landau-Vavilov dE/dx is described in the PDG chapter 33. Passage of particles through matter

	const Double_t K     = 0.307075;  // = 4*pi*Na*re^2*me*c^2  [MeV*cm2/mol]

	// Absorber material: P10 (Ar+CH4)
	const Double_t rho_P10 = 1.534*1.e-3;  // [g/cm3]

	// Z: atomic number
	const Double_t Z_Ar  = 18.;
	const Double_t Z_C   = 6.;
	const Double_t Z_H   = 1.;
	const Double_t Z_eff = 0.9*Z_Ar + 0.1*(Z_C+4.*Z_H);     // effective atomic number of P10
	// A: atomic mass [g/mol]
	const Double_t A_Ar  = 39.95;
	const Double_t A_C   = 12.01;
	const Double_t A_H   = 1.00794;
	const Double_t A_eff = 0.9*A_Ar + 0.1*(A_C+4.*A_H);     // effective atomic mass of P10
	// I: mean excitation energy [eV], values are obtained from Atomic Data and Nuclear Dta Tables 30, 261 (1984)
	const Double_t I_Ar    = 188.0*1.e-6;
	const Double_t I_CH4   = 41.7*1.e-6;
	const Double_t lnI_eff = (0.9*Z_Ar*TMath::Log(I_Ar) + 0.1*(Z_C+Z_H*4.)*TMath::Log(I_CH4))/Z_eff;

	// density correction
	Double_t delta_Ar(Double_t x);
	const Double_t C_Ar  = 11.948;
	const Double_t a_Ar  = 0.19714;
	const Double_t x0_Ar = 1.7635;
	const Double_t x1_Ar = 4.4855;
	const Double_t k_Ar  = 2.9618;

	Double_t delta_CH4(Double_t x);
	const Double_t C_CH4  = 9.5243;
	const Double_t a_CH4  = 0.09253;
	const Double_t x0_CH4 = 1.6263;
	const Double_t x1_CH4 = 3.9716;
	const Double_t k_CH4  = 3.6257;

	const Double_t ln10   = TMath::Log(10);

	Double_t fBBdedx(Double_t z, Double_t m, Double_t *x, Double_t *p);
	Double_t fLVdedx(Double_t z, Double_t m, Double_t *x, Double_t *p);

	Double_t fBBdedx_pim (Double_t *x, Double_t *p) { return fBBdedx(-1, kmpi,  x, p); }
	Double_t fBBdedx_pi  (Double_t *x, Double_t *p) { return fBBdedx( 1, kmpi,  x, p); }
	Double_t fBBdedx_p   (Double_t *x, Double_t *p) { return fBBdedx( 1, kmp,   x, p); }
	Double_t fBBdedx_d   (Double_t *x, Double_t *p) { return fBBdedx( 1, kmd,   x, p); }
	Double_t fBBdedx_t   (Double_t *x, Double_t *p) { return fBBdedx( 1, kmt,   x, p); }
	Double_t fBBdedx_he3 (Double_t *x, Double_t *p) { return fBBdedx( 2, kmhe3, x, p); }
	Double_t fBBdedx_al  (Double_t *x, Double_t *p) { return fBBdedx( 2, kmal,  x, p); }
	Double_t fBBdedx_he6 (Double_t *x, Double_t *p) { return fBBdedx( 2, kmhe6, x, p); }
	Double_t fBBdedx_li6 (Double_t *x, Double_t *p) { return fBBdedx( 3, kmli6, x, p); }
	Double_t fBBdedx_li7 (Double_t *x, Double_t *p) { return fBBdedx( 3, kmli7, x, p); }

	Double_t fLVdedx_p   (Double_t *x, Double_t *p) { return fLVdedx( 1, kmp,   x, p); }
	Double_t fLVdedx_d   (Double_t *x, Double_t *p) { return fLVdedx( 1, kmd,   x, p); }
	Double_t fLVdedx_t   (Double_t *x, Double_t *p) { return fLVdedx( 1, kmt,   x, p); }
	Double_t fLVdedx_he3 (Double_t *x, Double_t *p) { return fLVdedx( 2, kmhe3, x, p); }
	Double_t fLVdedx_al  (Double_t *x, Double_t *p) { return fLVdedx( 2, kmal,  x, p); }
	Double_t fLVdedx_he6 (Double_t *x, Double_t *p) { return fLVdedx( 2, kmhe6, x, p); }
	Double_t fLVdedx_li6 (Double_t *x, Double_t *p) { return fLVdedx( 3, kmli6, x, p); }
	Double_t fLVdedx_li7 (Double_t *x, Double_t *p) { return fLVdedx( 3, kmli7, x, p); }

	Double_t BBMassFinderEq(Double_t *x, Double_t *p);
	Double_t LVMassFinderEq(Double_t *x, Double_t *p);

	Double_t CalcBBMass(Double_t* p);
	Double_t CalcLVMass(Double_t* p);

}

Double_t MassEstimator::delta_Ar(Double_t x) // x: log10(beta*gamma)
{
	Double_t d_Ar;
	if(x<x0_Ar)                d_Ar = 0.;
	else if(x>=x0_Ar&&x<x1_Ar) d_Ar = 2.*ln10*x - C_Ar + a_Ar*TMath::Power(x1_Ar-x,k_Ar);
	else if(x>=x1_Ar)          d_Ar = 2.*ln10*x - C_Ar;
	return d_Ar;
}

Double_t MassEstimator::delta_CH4(Double_t x)
{
	Double_t d_CH4;
	if(x<x0_CH4)                 d_CH4 = 0.;
	else if(x>=x0_CH4&&x<x1_CH4) d_CH4 = 2.*ln10*x - C_CH4 + a_CH4*TMath::Power(x1_CH4-x,k_CH4);
	else if(x>=x1_CH4)           d_CH4 = 2.*ln10*x - C_CH4;
	return d_CH4;
}

Double_t MassEstimator::fBBdedx(Double_t z, Double_t m, Double_t *x, Double_t *p)
{
	// variable: x[0] = rigidity magnitude
	// parameters:
	// par[0] = normalization [MeV/cm]->[ADC/mm], par[1] = offset
	Double_t mom  = x[0]*z;
	Double_t b2   = mom*mom/(mom*mom+m*m);
	Double_t g2   = 1./(1.-b2);
	Double_t g    = TMath::Sqrt(g2);
	Double_t Wmax = 2.*kme*b2*g2/(1.+2.*g*kme/m+TMath::Power(kme/m,2.));

	Double_t X     = TMath::Log10(TMath::Sqrt(b2*g2));
	Double_t d_Ar  = delta_Ar(X);
	Double_t d_CH4 = delta_CH4(X);
	Double_t delta_eff = (0.9*Z_Ar*d_Ar+0.1*(Z_C+Z_H*4.)*d_CH4)/Z_eff;

	// Bethe-Bloch dedx [MeV/cm]
	Double_t dedx  = K*rho_P10*z*z*Z_eff/A_eff/b2*(0.5*TMath::Log(2.*kme*b2*g2*Wmax)-lnI_eff-b2-0.5*delta_eff);

	return p[0]*dedx+p[1];
}

Double_t MassEstimator::BBMassFinderEq(Double_t *x, Double_t *p)
{
	// f(x)=0 equation for root-finder
	// in this case, dedx_measured - dedx_calculated = 0 where 1d-variable is mass
	// parameters:
	// par[0],par[1] same as fBBdedx
	// par[2] = z(charge), par[3] = rigidity magnitude, par[4] = measured dedx;
	Double_t m    = x[0];
	Double_t z    = p[2];
	Double_t mom  = p[3]*z;
	Double_t b2   = mom*mom/(mom*mom+m*m);
	Double_t g2   = 1./(1.-b2);
	Double_t g    = TMath::Sqrt(g2);
	Double_t Wmax = 2.*kme*b2*g2/(1.+2.*g*kme/m+TMath::Power(kme/m,2.));

	Double_t X     = TMath::Log10(TMath::Sqrt(b2*g2));
	Double_t d_Ar  = delta_Ar(X);
	Double_t d_CH4 = delta_CH4(X);
	Double_t delta_eff = (0.9*Z_Ar*d_Ar+0.1*(Z_C+Z_H*4.)*d_CH4)/Z_eff;

	Double_t dedx  = K*rho_P10*z*z*Z_eff/A_eff/b2*(0.5*TMath::Log(2.*kme*b2*g2*Wmax)-lnI_eff-b2-0.5*delta_eff);

	return p[4] - p[0]*dedx-p[1];
}

Double_t MassEstimator::CalcBBMass(Double_t* p)
{
	TF1 bbfit("bbfit",BBMassFinderEq,-500.,5000.,5,1);    // name, function, xmin, xmax, n-parameter, dimension
	bbfit.SetParameters(p);
	ROOT::Math::RootFinder finder(ROOT::Math::RootFinder::kBRENT);
	ROOT::Math::WrappedTF1 wf(bbfit);
	finder.SetFunction(wf,0.1,10000.);
	finder.Solve();
	return finder.Root();
}


Double_t MassEstimator::fLVdedx(Double_t z, Double_t m, Double_t *x, Double_t *p)
{
	// parameters:
	// par[0] = normalization, par[1] = offset, par[2] = detector thickness in [cm].
	Double_t mom  = x[0]*z;
	Double_t b2   = mom*mom/(mom*mom+m*m);
	Double_t g2   = 1./(1.-b2);

	Double_t X     = TMath::Log10(TMath::Sqrt(b2*g2));
	Double_t d_Ar  = delta_Ar(X);
	Double_t d_CH4 = delta_CH4(X);
	Double_t delta_eff = (0.9*Z_Ar*d_Ar+0.1*(Z_C+Z_H*4.)*d_CH4)/Z_eff;

	// detector depth is parameter
	Double_t t    = rho_P10*p[2];
	Double_t xi   = K/2.*Z_eff/A_eff*z*z/b2*t; 
	// Landau-Vavilov most probable energy loss [MeV]
	Double_t delta_p = xi*(TMath::Log(2.*kme*b2*g2)+TMath::Log(xi)-2.*lnI_eff+0.2-b2-delta_eff);

	return p[0]*delta_p/p[2]+p[1];
}

Double_t MassEstimator::LVMassFinderEq(Double_t *x, Double_t *p)
{
	Double_t m    = x[0];
	Double_t z    = p[3];
	Double_t mom  = p[4]*z;
	Double_t b2   = mom*mom/(mom*mom+m*m);
	Double_t g2   = 1./(1.-b2);

	Double_t X     = TMath::Log10(TMath::Sqrt(b2*g2));
	Double_t d_Ar  = delta_Ar(X);
	Double_t d_CH4 = delta_CH4(X);
	Double_t delta_eff = (0.9*Z_Ar*d_Ar+0.1*(Z_C+Z_H*4.)*d_CH4)/Z_eff;

	// detector depth is parameter
	Double_t t    = rho_P10*p[2];
	Double_t xi   = K/2.*Z_eff/A_eff*z*z/b2*t; 
	// Landau-Vavilov most probable energy loss [MeV]
	Double_t delta_p = xi*(TMath::Log(2.*kme*b2*g2)+TMath::Log(xi)-2.*lnI_eff+0.2-b2-delta_eff);

	return p[6] - (p[0]*delta_p/p[2]+p[1]);
}

Double_t MassEstimator::CalcLVMass(Double_t* p)
{
	TF1 lvfit("lvfit",LVMassFinderEq,-500.,5000.,6,1);    // name, function, xmin, xmax, n-parameter, dimension
	lvfit.SetParameters(p);
	ROOT::Math::RootFinder finder(ROOT::Math::RootFinder::kBRENT);
	ROOT::Math::WrappedTF1 wf(lvfit);
	finder.SetFunction(wf,0.1,10000.);
	finder.Solve();
	return finder.Root();
}
