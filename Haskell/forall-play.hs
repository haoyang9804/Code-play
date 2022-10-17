-- https://wasp-lang.dev/blog/2021/09/01/haskell-forall-tutorial

{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE ExistentialQuantification #-}

---------- This is a ScipedTypeVariables example

f :: forall a. [a] -> [a]
f xs = ys ++ ys
  where ys :: [a]
        ys = reverse xs

-- Without `forall`, the code cannot compile
-- since the polymorphic type `a` in `ys::[a]`
-- is not promised to be the same as the `a` in
-- `[a] -> [a]`


---------- This is a RankNTypes example

foo :: (forall a. a -> a) -> (Char, Bool)    -- We can do this only with RankNTypes.
foo func = undefined

-- We cannot define `foo = undefined` in the above example 
-- since (forall a. a -> a) must be a type of function

bar :: forall a. ((a -> a) -> (Char, Bool))  -- This is usual stuff, we don't need RankNTypes for it. Actually we can even drop `forall` since it is implicit.
bar = undefined

-- `forall a. ((a -> a) -> (Char, Bool))` could be the type
-- of `undefined`. I guess any explicit or implicit forall
-- expression could be the type of `undefined`


---------- This is an ExistentialQuantification example

-- data Showable = forall s. (Show s) => Showable s
data Showable = forall s. (Show s) => Showable s

someShowables :: [Showable]
someShowables = [Showable "Hi", Showable 5, Showable (1, 2)]

printShowables :: [Showable] -> IO ()
printShowables = mapM_ (\(Showable s) -> print s)

main :: IO ()
main = printShowables someShowables

-- In this example, we create a heterogeneous list
-- containing diverse Showable contents

-- The noteworthy thing is `forall` here is like an
-- existential quantifier

-- If we define `Showable` in regular way without forall,
-- then it looks like
--      data Showable s = Show s => Showable s
-- by which we cannot define `someShowables` since
-- `Showable` requires a type parameter.