template <typename FLT = double>
class FitLineY{
private: std::vector<FLT>
std::vector<FLT> m_mat;
std::vector<FLT> m_ths;
std::vector<FLT> m_cov;
std::vector<FLT> m_sol;
std::vector<std::string> m_names;

std::vector<FLT> m_wgrad;
std::vector<size_t> m_multiidx;

}
