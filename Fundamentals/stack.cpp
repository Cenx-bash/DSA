#include <stack>

stack<int> st;

st.push(10);
st.push(20);

cout << st.top() << endl;

st.pop();

cout << st.empty();