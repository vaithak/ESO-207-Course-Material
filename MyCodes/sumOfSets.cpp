#include <iostream>
#include <complex>
#include <vector>

using namespace std;

vector<complex<double> > fft(vector<complex<double> >& a, int notInverse=1) 
{ 
    int n = a.size(); 

    if (n == 1) 
        return vector<complex<double> >(1, a[0]); 

    vector<complex<double> > w(n); 
    for (int i = 0; i < n; i++) { 
        double alpha = 2 * M_PI * i / n; 
        w[i] = complex<double> (cos(alpha), (notInverse)*sin(alpha)); 
    } 
  
    vector<complex<double> > A0(n / 2), A1(n / 2); 
    for (int i = 0; i < n / 2; i++) { 
        A0[i] = a[i * 2]; 
        A1[i] = a[i * 2 + 1]; 
    } 
 
    vector<complex<double> > y0 = fft(A0,notInverse);  
    vector<complex<double> > y1 = fft(A1,notInverse); 

    vector<complex<double> > y(n); 
    for (int k = 0; k < n / 2; k++) { 
        y[k] = y0[k] + w[k] * y1[k]; 
        y[k + n / 2] = y0[k] - w[k] * y1[k]; 
    } 
    return y; 
} 

void multiply(vector<complex<double> > &a,vector<complex<double> > &b, vector<complex<double> >&res)
{
    int n = a.size();
    int temp=2*n;
    int size=1;
    while(size<temp)
        size*=2;

    while(n<size)
    {
        a.push_back(complex<double>(0.0,0.0));
        b.push_back(complex<double>(0.0,0.0));
        n++;
    }
    
    vector<complex<double> > pa = fft(a);
    vector<complex<double> > pb = fft(b);
    vector<complex<double> > pc(size);
    for(int i=0;i<size;i++)
    {
        pc[i]=pa[i]*pb[i];
    }
    
    vector<complex<double> > c = fft(pc,-1);
    
    for(int i=0;i<(temp - 1); i++)
    {
        double test = c[i].real()/size;
        res.push_back(test);
    }
    
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<complex<double> >a(10*n + 1,complex<double>(0.0,0.0));
        vector<complex<double> >b(10*n + 1,complex<double>(0.0,0.0));
    
        for(int i=0;i<n;i++)
        {
            int temp;
            cin>>temp;
            double check = a[temp].real() + 1;
            a[temp].real(check);
        }
    
        for(int i=0;i<n;i++)
        {
            int temp;
            cin>>temp;
            double check = b[temp].real() + 1;
            b[temp].real(check);
        }
        
        vector<complex<double> >res;
        multiply(a,b,res);
        
        int count=0;
        for(int i=0;i<=(20*n); i++)
        {
            if(abs(res[i].real())>=10e-5)
            {
                count++;
            }
        }
        cout<<count<<endl;
        
        for(int i=0;i<=(20*n); i++)
        {
            if(abs(res[i].real())>=10e-5)
            {
                cout<<i<<" "<<res[i].real()<<endl;
            }
        }
    }

    return 0;
}
