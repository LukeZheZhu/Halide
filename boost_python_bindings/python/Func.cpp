#include "Func.h"

// to avoid compiler confusion, python.hpp must be include before Halide headers
#include <boost/python.hpp>
#include "add_operators.h"

#include "../../src/Func.h"

#include <vector>
#include <string>

namespace h = Halide;
namespace p = boost::python;
using p::self;


h::Realization func_realize0(h::Func &that, std::vector<int32_t> sizes, const h::Target &target = h::Target())
{
    return that.realize(sizes, target);
}

BOOST_PYTHON_FUNCTION_OVERLOADS( func_realize0_overloads, func_realize0, 2, 3)


h::Realization func_realize1(h::Func &that, int x_size=0, int y_size=0, int z_size=0, int w_size=0,
                             const h::Target &target = h::Target())
{
    return that.realize(x_size, y_size, z_size, w_size, target);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(func_realize1_overloads, func_realize1, 1, 6)


void func_compile_jit(h::Func &that)
{
    that.compile_jit();
    return;
}


void func_compile_to_bitcode0(h::Func &that, const std::string &filename,
                              const std::vector<h::Argument> &args,
                              const std::string fn_name = "",
                              const h::Target &target = h::get_target_from_environment())
{
    that.compile_to_bitcode(filename, args, fn_name, target);
    return;
}


BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_bitcode0_overloads, func_compile_to_bitcode0, 3, 5)


void func_compile_to_c0(h::Func &that, const std::string &filename,
                        const std::vector<h::Argument> &args,
                        const std::string fn_name = "",
                        const h::Target &target = h::get_target_from_environment())
{
    that.compile_to_c(filename, args, fn_name, target);
    return;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_c0_overloads, func_compile_to_c0, 3, 5)


void func_compile_to_file0(h::Func &that, const std::string &filename_prefix,
                           const std::vector<h::Argument> &args,
                           const h::Target &target = h::get_target_from_environment())
{
    that.compile_to_file(filename_prefix, args, target);
    return;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(func_compile_to_file0_overloads, func_compile_to_file0, 3, 4)


h::Func &func_parallel0(h::Func &that, h::VarOrRVar var)
{
    return that.parallel(var);
}


h::Func &func_parallel1(h::Func &that, h::VarOrRVar var, int factor)
{
    return that.parallel(var, factor);
}


void func_vectorize0(h::Func &that, h::VarOrRVar var)
{
    that.vectorize(var);
}

void func_vectorize1(h::Func &that, h::VarOrRVar var, int factor)
{
    that.vectorize(var, factor);
}

h::Func &func_store_at0(h::Func &that, h::Func f, h::Var var)
{
    return that.store_at(f, var);
}

h::Func &func_store_at1(h::Func &that, h::Func f, h::RVar var)
{
    return that.store_at(f, var);
}

h::Func &func_compute_at0(h::Func &that, h::Func f, h::Var var)
{
    return that.compute_at(f, var);
}

h::Func &func_compute_at1(h::Func &that, h::Func f, h::RVar var)
{
    return that.compute_at(f, var);
}


/// Define all gpu related methods
template<typename T>
void defineFuncGpuMethods(T &func_class)
{


    /*
                                                                &Func::gpu_threads(self, *args):
                                                                """
                                                                Tell Halide that the following dimensions correspond to cuda
                                                                thread indices. This is useful if you compute a producer
                                                                function within the block indices of a consumer function, and
                                                                want to control how that function's dimensions map to cuda
                                                                threads. If the selected target is not ptx, this just marks
                                                                those dimensions as parallel.
                                                                """

                                                                &Func::gpu_single_thread(self, *args):
                                                                """
                                                                Tell Halide to run this stage using a single gpu thread and
                                                                block. This is not an efficient use of your GPU, but it can be
                                                                useful to avoid copy-back for intermediate update stages that
                                                                touch a very small part of your Func.
                                                                """

                                                                &Func::gpu_blocks(self, *args):
                                                                """
                                                                Tell Halide that the following dimensions correspond to cuda
                                                                block indices. This is useful for scheduling stages that will
                                                                run serially within each cuda block. If the selected target is
                                                                not ptx, this just marks those dimensions as parallel.
                                                                """

                                                                &Func::gpu(self, block_x, thread_x):
                                                                """
                                                                Three signatures::

                                                                gpu(block_x, thread_x)
                                                                gpu(block_x, block_y, thread_x, thread_y)
                                                                gpu(block_x, block_y, block_z, thread_x, thread_y, thread_z)

                                                                Tell Halide that the following dimensions correspond to cuda
                                                                block indices and thread indices. If the selected target is not
                                                                ptx, these just mark the given dimensions as parallel. The
                                                                dimensions are consumed by this call, so do all other
                                                                unrolling, reordering, etc first.
                                                                """

                                                                &Func::gpu_tile(self, x, x_size):
                                                                """
                                                                Three signatures:

                                                                gpu_tile(x, x_size)
                                                                gpu_tile(x, y, x_size, y_size)
                                                                gpu_tile(x, y, z, x_size, y_size, z_size)

                                                                Short-hand for tiling a domain and mapping the tile indices
                                                                to cuda block indices and the coordinates within each tile to
                                                                cuda thread indices. Consumes the variables given, so do all
                                                                other scheduling first.
                                                                """

                                                                &Func::cuda_threads(self, *args):
                                                                """
                                                                deprecated Old name for #gpu_threads.
                                                                Tell Halide that the following dimensions correspond to cuda
                                                                thread indices. This is useful if you compute a producer
                                                                function within the block indices of a consumer function, and
                                                                want to control how that function's dimensions map to cuda
                                                                threads. If the selected target is not ptx, this just marks
                                                                those dimensions as parallel.
                                                                """

                                                                &Func::cuda_blocks(self, *args):
                                                                """
                                                                deprecated Old name for #cuda_blocks.
                                                                Tell Halide that the following dimensions correspond to cuda
                                                                block indices. This is useful for scheduling stages that will
                                                                run serially within each cuda block. If the selected target is
                                                                not ptx, this just marks those dimensions as parallel.
                                                                """

                                                                &Func::cuda(self, block_x, thread_x):
                                                                """
                                                                deprecated Old name for #cuda.
                                                                Three signatures::

                                                                cuda(block_x, thread_x)
                                                                cuda(block_x, block_y, thread_x, thread_y)
                                                                cuda(block_x, block_y, block_z, thread_x, thread_y, thread_z)

                                                                Tell Halide that the following dimensions correspond to cuda
                                                                block indices and thread indices. If the selected target is not
                                                                ptx, these just mark the given dimensions as parallel. The
                                                                dimensions are consumed by this call, so do all other
                                                                unrolling, reordering, etc first.
                                                                """

                                                                &Func::cuda_tile(self, x, x_size):
                                                                """
                                                                deprecated Old name for #cuda_tile.
                                                                Three signatures:

                                                                cuda_tile(x, x_size)
                                                                cuda_tile(x, y, x_size, y_size)
                                                                cuda_tile(x, y, z, x_size, y_size, z_size)

                                                                Short-hand for tiling a domain and mapping the tile indices
                                                                to cuda block indices and the coordinates within each tile to
                                                                cuda thread indices. Consumes the variables given, so do all
                                                                other scheduling first.
                                                                """


*/
    return;
}


void tuple_to_var_expr_vector(const p::tuple &args_passed,
                              std::vector<h::Var> &var_args,
                              std::vector<h::Expr> &expr_args)
{
    const size_t args_len = p::len(args_passed);
    for(size_t i=0; i < args_len; i+=1)
    {
        p::object o = args_passed[i];
        p::extract<h::Var &> var_extract(o);
        p::extract<h::Expr &> expr_extract(o);

        if(var_extract.check())
        {
            h::Var v = var_extract();
            var_args.push_back(v);

            expr_args.push_back(v); // is this really what we want ?
        }

        if(expr_extract.check())
        {
            h::Expr e = expr_extract();
            expr_args.push_back(e);
        }

        if((var_extract.check() == false) and (expr_extract.check() == false))
        {
            for(size_t j=0; j < args_len; j+=1)
            {
                p::object o = args_passed[j];
                const std::string o_str = p::extract<std::string>(p::str(o));
                printf("Func args_passed[%lu] == %s\n", j, o_str.c_str());
            }
            throw std::invalid_argument("Func::operator() only handles a list of Var or a list of (convertible to) Expr.");
        }
    }

    return;
}

p::object func_getitem_operator0(h::Func &that, p::tuple args_passed)
{
    std::vector<h::Var> var_args;
    std::vector<h::Expr> expr_args;
    const size_t args_len = p::len(args_passed);

    tuple_to_var_expr_vector(args_passed, var_args, expr_args);


    p::object return_object;

    // We prioritize Args over Expr variant
    if(var_args.size() == args_len)
    {
        h::FuncRefVar ret = that(var_args);

        p::copy_non_const_reference::apply<h::FuncRefVar &>::type converter;
        PyObject* obj = converter( ret );
        return_object = p::object( p::handle<>( obj ) );
    }
    else
    {   user_assert(expr_args.size() == args_len) << "Not all func_getitem_operator0 arguments where converted to Expr";
        h::FuncRefExpr ret = that(expr_args);

        p::copy_non_const_reference::apply<h::FuncRefExpr &>::type converter;
        PyObject* obj = converter( ret );
        return_object = p::object( p::handle<>( obj ) );
    }

    return return_object;
}


template <typename T>
h::Stage func_setitem_operator0(h::Func &that, p::tuple args_passed, T right_hand)
{
    std::vector<h::Var> var_args;
    std::vector<h::Expr> expr_args;
    const size_t args_len = p::len(args_passed);

    tuple_to_var_expr_vector(args_passed, var_args, expr_args);

    // We prioritize Args
    if(var_args.size() == args_len)
    {
        h::FuncRefVar ret = that(var_args);
        h::Stage s = (ret = right_hand);
        return s;
    }
    else
    {   user_assert(expr_args.size() == args_len) << "Not all func_setitem_operator0 arguments where converted to Expr";

        h::FuncRefExpr ret = that(expr_args);
        h::Stage s = (ret = right_hand);
        return s;
    }
}

template<typename A, typename B>
auto add_func_refs(A &a, B &b) -> decltype(a + b)
{
    return a + b;
}

template<typename A, typename B>
auto sub_func_refs(A &a, B &b) -> decltype(a - b)
{
    return a - b;
}

template<typename A, typename B>
auto mul_func_refs(A &a, B &b) -> decltype(a * b)
{
    return a * b;
}

template<typename A, typename B>
auto div_func_refs(A &a, B &b) -> decltype(a / b)
{
    return a / b;
}

template<typename A, typename B>
auto mod_func_refs(A &a, B &b) -> decltype(a % b)
{
    return a % b;
}

template<typename A, typename B>
auto and_func_refs(A &a, B &b) -> decltype(a & b)
{
    return a & b;
}

template<typename A, typename B>
auto xor_func_refs(A &a, B &b) -> decltype(a ^ b)
{
    return a ^ b;
}

template<typename A, typename B>
auto or_func_refs(A &a, B &b) -> decltype(a | b)
{
    return a | b;
}

template<typename A, typename B>
auto gt_func_refs(A &a, B &b) -> decltype(a > b)
{
    return a > b;
}

template<typename A, typename B>
auto ge_func_refs(A &a, B &b) -> decltype(a >= b)
{
    return a >= b;
}

template<typename A, typename B>
auto lt_func_refs(A &a, B &b) -> decltype(a < b)
{
    return a < b;
}

template<typename A, typename B>
auto le_func_refs(A &a, B &b) -> decltype(a <= b)
{
    return a <= b;
}

template<typename A, typename B>
auto eq_func_refs(A &a, B &b) -> decltype(a == b)
{
    return a == b;
}

template<typename A, typename B>
auto ne_func_refs(A &a, B &b) -> decltype(a != b)
{
    return a != b;
}


template<typename PythonClass, typename B>
void add_func_ref_operators_with(PythonClass &class_a)
{
    typedef typename PythonClass::wrapped_type T;

    class_a
            .def("__add__", &add_func_refs<T, B>)
            .def("__sub__", &sub_func_refs<T, B>)
        #if PY_VERSION_HEX >= 0x03000000
            .def("__truediv__", &div_func_refs<T, B>)
        #else
            .def("__div__", &div_func_refs<T, B>)
        #endif
            .def("__mod__", &mod_func_refs<T, B>)
            .def("__and__", &and_func_refs<T, B>)
            .def("__xor__", &xor_func_refs<T, B>)
            .def("__or__", &or_func_refs<T, B>)
            .def("__gt__", &gt_func_refs<T, B>)
            .def("__ge__", &gt_func_refs<T, B>)
            .def("__lt__", &lt_func_refs<T, B>)
            .def("__le__", &le_func_refs<T, B>)
            .def("__eq__", &eq_func_refs<T, B>)
            .def("__ne__", &ne_func_refs<T, B>)
            ;

    //    BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
    //    BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)

    return;
}

void defineFuncRef()
{
    using Halide::FuncRefVar;
    using Halide::FuncRefExpr;
    using p::self;

    // only defined so that boost::python knows about these classes,
    // not (yet) meant to be created or manipulated by the user
    auto func_ref_var_class =
            p::class_<FuncRefVar>("FuncRefVar", p::no_init)
            ;

    add_func_ref_operators_with<decltype(func_ref_var_class), FuncRefVar>(func_ref_var_class);
    add_func_ref_operators_with<decltype(func_ref_var_class), FuncRefExpr>(func_ref_var_class);

    auto func_ref_expr_class =
            p::class_<FuncRefExpr>("FuncRefExpr", p::no_init)
            ;

    add_func_ref_operators_with<decltype(func_ref_expr_class), FuncRefVar>(func_ref_expr_class);
    add_func_ref_operators_with<decltype(func_ref_expr_class), FuncRefExpr>(func_ref_expr_class);

    p::implicitly_convertible<FuncRefVar, h::Expr>();
    p::implicitly_convertible<FuncRefExpr, h::Expr>();

    return;
}

void defineVarOrRVar()
{
    using Halide::VarOrRVar;

    p::class_<VarOrRVar>("VarOrRVar",
                         "A class that can represent Vars or RVars. "
                         "Used for reorder calls which can accept a mix of either.",
                         p::init<std::string, bool>(p::args("n", "r")))
            .def(p::init<h::Var>(p::arg("v")))
            .def(p::init<h::RVar>(p::arg("r")))
            .def(p::init<h::RDom>(p::arg("r")))
            .def("name", &VarOrRVar::name, p::return_value_policy<p::copy_const_reference>())
            .def_readonly("var", &VarOrRVar::var)
            .def_readonly("rvar", &VarOrRVar::rvar)
            .def_readonly("is_rvar", &VarOrRVar::is_rvar)
            ;


    p::implicitly_convertible<h::Var, VarOrRVar>();
    p::implicitly_convertible<h::RVar, VarOrRVar>();
    p::implicitly_convertible<h::RDom, VarOrRVar>();

    return;
}

void defineStage()
{
    using Halide::Stage;

    // only defined so that boost::python knows about these classes,
    // not (yet) meant to be created or manipulated by the user
    p::class_<Stage>("Stage", p::no_init);

    return;
}

void defineFunc()
{
    using Halide::Func;

    auto func_class = p::class_<Func>("Func",
                                      "A halide function. This class represents one stage in a Halide" \
                                      "pipeline, and is the unit by which we schedule things. By default" \
                                      "they are aggressively inlined, so you are encouraged to make lots" \
                                      "of little functions, rather than storing things in Exprs.\n" \
                                      "Constructors::\n\n" \
                                      "  Func()      -- Declare a new undefined function with an automatically-generated unique name\n" \
                                      "  Func(expr)  -- Declare a new function with an automatically-generated unique\n" \
                                      "                 name, and define it to return the given expression (which may\n" \
                                      "                 not contain free variables).\n" \
                                      "  Func(name)  -- Declare a new undefined function with the given name",
                                      p::init<>())
            .def(p::init<std::string>())
            .def(p::init<h::Expr>());
    //.def("set", &Func::set, "Typically one uses f[x, y] = expr to assign to a function. However f.set(expr) can be used also.")

    func_class.def("allow_race_conditions",
                   &Func::allow_race_conditions,
                   p::return_internal_reference<1>(),
                   "Specify that race conditions are permitted for this Func, "
                   "which enables parallelizing over RVars even when Halide cannot "
                   "prove that it is safe to do so. Use this with great caution, "
                   "and only if you can prove to yourself that this is safe, as it "
                   "may result in a non-deterministic routine that returns "
                   "different values at different times or on different machines.");

    func_class.def("realize",
                   &func_realize1,
                   func_realize1_overloads(
                       p::args("x_size", "y_size", "z_size", "w_size", "target"),
                       "Evaluate this function over some rectangular domain and return"
                       "the resulting buffer. The buffer should probably be instantly"
                       "wrapped in an Image class.\n\n" \
                       "One can use f.realize(Buffer) to realize into an existing buffer."))
            .def("realize", &func_realize0, func_realize0_overloads(
                     p::args("sizes", "target")));


    func_class.def("compile_to_bitcode",
                   &func_compile_to_bitcode0,
                   func_compile_to_bitcode0_overloads(
                       p::args("filename", "args", "fn_name", "target"),
                       "Statically compile this function to llvm bitcode, with the "
                       "given filename (which should probably end in .bc), type "
                       "signature, and C function name (which defaults to the same name "
                       "as this halide function."));

    func_class.def("compile_to_c",
                   &func_compile_to_c0,
                   func_compile_to_c0_overloads(
                       p::args("filename", "args", "fn_name", "target"),
                       "Statically compile this function to C source code. This is "
                       "useful for providing fallback code paths that will compile on "
                       "many platforms. Vectorization will fail, and parallelization "
                       "will produce serial code."));

    func_class.def("compile_to_file",
                   &func_compile_to_file0,
                   func_compile_to_file0_overloads(
                       p::args("filename_prefix", "args", "target"),
                       "Compile to object file and header pair, with the given arguments. "
                       "Also names the C function to match the first argument."));

    func_class.def("compile_jit",
                   &func_compile_jit,
                   "Eagerly jit compile the function to machine code. This "
                   "normally happens on the first call to realize. If you're "
                   "running your halide pipeline inside time-sensitive code and "
                   "wish to avoid including the time taken to compile a pipeline, "
                   "then you can call this ahead of time. Returns the raw function "
                   "pointer to the compiled pipeline.");

    func_class.def("debug_to_file", &Func::debug_to_file, p::arg("filename"),
                   "When this function is compiled, include code that dumps its values "
                   "to a file after it is realized, for the purpose of debugging. "
                   "The file covers the realized extent at the point in the schedule that "
                   "debug_to_file appears.\n"
                   "If filename ends in \".tif\" or \".tiff\" (case insensitive) the file "
                   "is in TIFF format and can be read by standard tools.");

    func_class.def("name", &Func::name,
                   p::return_value_policy<p::copy_const_reference>(),
                   "The name of this function, either given during construction, or automatically generated.");

    func_class.def("value", &Func::value,
                   "The right-hand-side value of the pure definition of this "
                   "function. May be undefined if the function has no pure definition yet.");

    func_class.def("dimensions", &Func::dimensions,
                   "The dimensionality (number of arguments) of this function. Zero if the function is not yet defined.");


    func_class.def("__getitem__", &func_getitem_operator0,
                   "If received a tuple of Vars\n\n"
                   "Construct either the left-hand-side of a definition, or a call "
                   "to a functions that happens to only contain vars as "
                   "arguments. If the function has already been defined, and fewer "
                   "arguments are given than the function has dimensions, then "
                   "enough implicit vars are added to the end of the argument list "
                   "to make up the difference (see \ref Var::implicit)\n\n"
                   "If received a tuple of Expr\n\n"
                   "Either calls to the function, or the left-hand-side of a "
                   "update definition (see \ref RDom). If the function has "
                   "already been defined, and fewer arguments are given than the "
                   "function has dimensions, then enough implicit vars are added to "
                   "the end of the argument list to make up the difference. (see \ref Var::implicit)");

    func_class.def("__setitem__", &func_setitem_operator0<h::FuncRefVar>);
    func_class.def("__setitem__", &func_setitem_operator0<h::FuncRefExpr>);
    func_class.def("__setitem__", &func_setitem_operator0<h::Expr>);

    /*
                                                                        &Func::__getitem__(self, *args):
                                                                        """
                                                                        Either calls to the function, or the left-hand-side of a
                                                                        reduction definition (see \ref RDom). If the function has
                                                                        already been defined, and fewer arguments are given than the
                                                                        function has dimensions, then enough implicit vars are added to
                                                                        the end of the argument list to make up the difference.
                                                                        """

                                                                        &Func::split(self, old, outer, inner, factor):
                                                                        """
                                                                        Split a dimension into inner and outer subdimensions with the
                                                                        given names, where the inner dimension iterates from 0 to
                                                                        factor-1. The inner and outer subdimensions can then be dealt
                                                                        with using the other scheduling calls. It's ok to reuse the old
                                                                        variable name as either the inner or outer variable.

                                                                        The arguments are all Var instances.
                                                                        """

                                                                        &Func::fuse(self, inner, outer, fused):
                                                                        """
                                                                        Join two dimensions into a single fused dimension. The fused
                                                                        dimension covers the product of the extents of the inner and
                                                                        outer dimensions given.
                                                                        """
        */

    func_class.def("parallel", &func_parallel0, p::arg("var"),
                   p::return_internal_reference<1>(),
                   "Mark a dimension (Var instance) to be traversed in parallel.")
            .def("parallel", &func_parallel1, p::args("var", "factor"),
                 p::return_internal_reference<1>());

    func_class.def("vectorize",
                   &func_vectorize1,
                   p::args("var", "factor"),
                   "Split a dimension (Var instance) by the given int factor, then vectorize the "
                   "inner dimension. This is how you vectorize a loop of unknown "
                   "size. The variable to be vectorized should be the innermost "
                   "one. After this call, var refers to the outer dimension of the "
                   "split.")
            .def("vectorize",
                 &func_vectorize0,
                 p::arg("var"));

    /*
                                                                &Func::unroll(self, var, factor=None):
                                                                """
                                                                Split a dimension (Var instance) by the given int factor, then unroll the inner
                                                                dimension. This is how you unroll a loop of unknown size by
                                                                some constant factor. After this call, var refers to the outer
                                                                dimension of the split.
                                                                """

                                                                &Func::bound(self, min_expr, extent_expr):
                                                                """
                                                                Statically declare that the range over which a function should
                                                                be evaluated is given by the second and third arguments. This
                                                                can let Halide perform some optimizations. E.g. if you know
                                                                there are going to be 4 color channels, you can completely
                                                                vectorize the color channel dimension without the overhead of
                                                                splitting it up. If bounds inference decides that it requires
                                                                more of this function than the bounds you have stated, a
                                                                runtime error will occur when you try to run your pipeline.
                                                                """

                                                                &Func::tile(self, x, y, xo, yo, xi, yi, xfactor, yfactor):
                                                                """
                                                                Traverse in tiled order. Two signatures::

                                                                tile(x, y, xi, yi, xfactor, yfactor)
                                                                tile(x, y, xo, yo, xi, yi, xfactor, yfactor)

                                                                Split two dimensions at once by the given factors, and then
                                                                reorder the resulting dimensions to be xi, yi, xo, yo from
                                                                innermost outwards. This gives a tiled traversal.

                                                                The shorter form of tile reuses the old variable names as
                                                                the new outer dimensions.
                                                                """

                                                                &Func::reorder(self, *args):
                                                                """
                                                                Reorder the dimensions (Var arguments) to have the given nesting
                                                                order, from innermost loop order to outermost.
                                                                """
*/


    func_class.def("rename",
                   &Func::rename,
                   p::args("old_name", "new_name"),
                   p::return_internal_reference<1>(),
                   "Rename a dimension. Equivalent to split with a inner size of one.");


    /*
                                                                &Func::reorder_storage(self, *args):
                                                                """
                                                                Scheduling calls that control how the storage for the function
                                                                is laid out. Right now you can only reorder the dimensions.
                                                                """
*/

    func_class.def("compute_at",
                   &func_compute_at0,
                   p::args("f", "var"),
                   p::return_internal_reference<1>(),
                   "Compute this function as needed for each unique value of the "
                   "given var (can be a Var or an RVar) for the given calling function f.")
            .def("compute_at",
                 &func_compute_at1,
                 p::args("f", "var"),
                 p::return_internal_reference<1>());

    func_class.def("compute_root",
                   &Func::compute_root,
                   p::return_internal_reference<1>(),
                   "Compute all of this function once ahead of time.");


    func_class.def("store_at",
                   &func_store_at0,
                   p::args("f", "var"),
                   p::return_internal_reference<1>(),
                   "Allocate storage for this function within f's loop over "
                   "var (can be a Var or an RVar). Scheduling storage is optional, and can be used to "
                   "separate the loop level at which storage occurs from the loop "
                   "level at which computation occurs to trade off between locality "
                   "and redundant work.")
            .def("store_at",
                 &func_store_at1,
                 p::args("f", "var"),
                 p::return_internal_reference<1>());

    func_class.def("store_root",
                   &Func::store_root,
                   p::return_internal_reference<1>(),
                   "Equivalent to Func.store_at, but schedules storage outside the outermost loop.");

    func_class.def("compute_inline",
                   &Func::compute_inline,
                   p::return_internal_reference<1>(),
                   "Aggressively inline all uses of this function. This is the "
                   "default schedule, so you're unlikely to need to call this. For "
                   "a reduction, that means it gets computed as close to the "
                   "innermost loop as possible.");

    func_class.def("update",
                   &Func::update,
                   "Get a handle on the update step of a reduction for the "
                   "purposes of scheduling it. Only the pure dimensions of the "
                   "update step can be meaningfully manipulated (see RDom).");

    func_class.def("function",
                   &Func::function,
                   "Get a handle on the internal halide function that this Func represents. "
                   "Useful if you want to do introspection on Halide functions.");

    defineFuncGpuMethods(func_class);

    p::implicitly_convertible<Func, h::Expr>();

    defineFuncRef();
    defineStage();
    defineVarOrRVar();

    return;
}
