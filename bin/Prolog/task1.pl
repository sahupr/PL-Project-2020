:- use_module(library(http/json)).
:- initialization main, halt.

process_data([], []).
process_data([Head|Tail], Result) :-
    process_person(Head, HeadResult),
    process_data(Tail, TailResult),
    append(HeadResult, TailResult, Result).

process_person(Person, Result) :-
    process_spread(Person.spread_radius, Person.movement_history, Result).

process_spread(_, [], []).
process_spread(_, [_|[]], []).
process_spread(SpreadRadius, [Head1|[Head2|Tail]], Result) :-
    to_figure(SpreadRadius, Head1, Head2, HeadResult),
    process_spread(SpreadRadius, [Head2|Tail], TailResult),
    append([HeadResult], TailResult, Result).

to_figure(SpreadRadius, [X1|[Y1|[]]], [X2|[Y2|[]]], [SpreadRadius, X1, Y1, X2, Y2]).

main :-
    current_input(InputStream),
    json_read_dict(InputStream, InputData),
    process_data(InputData.data, Result),
    OutputData = output_data{geometric_shapes:Result},
    current_output(OutputStream),
    json_write_dict(OutputStream, OutputData),
    nl.